#include "model.h"
#include <exception>
#include <optional>

std::string trim (std::string str) {
  str.erase(0, str.find_first_not_of(" "));
  str.erase(str.find_last_not_of(" ") + 1);
  return str;
}

Model::Model(std::string name, size_t n_states, size_t n_inputs)
    : _name(name), _n_inputs(n_inputs), _n_states(n_states) 
{
  _states.resize(_n_states, 0.0);
}

Model::~Model() {}

void Model::set_x0(Vec initial_states) {
  if(_states.size() != initial_states.size()) {
    throw std::invalid_argument("Invalid size");
  }
  _states = initial_states;

}

void Model::step(double dt, Vec inputs) {
  Vec x_dot = compute_x_dot(dt, inputs, _states);
  for(size_t i = 0; i<_n_states; i++) {
    _states[i] = _states[i] + dt * x_dot[i];
  }
  _t += dt;
  csv_row(_log_file);
}

void Model::step(double dt, Vec inputs, std::function<void(double dt, Vec states, Vec x_dot)> integrator) {
  Vec x_dot = compute_x_dot(dt, inputs, _states);

    integrator(dt, _states, x_dot);

    _t += dt;
    // Log current states
    log();
}

bool Model::start_log (std::string path) {
  std::string filename = path + "/" + _name + ".csv";
  _log_file.open(filename);
  if(_log_file.is_open()) {
    csv_header(_log_file);
  }
  return _log_file.is_open();
}
  
void Model::stop_log() {
  _log_file.close();
}

void Model::csv_header(std::ostream &out) {
  out << "t";
  for(size_t i = 0; i < _n_states; i++) {
    out << "," << "x" << i;
  }
  out << "\n";
}

void Model::csv_row(std::ostream &out) {
  out << _t;
  for(size_t i = 0; i < _n_states; i++) {
    out << "," << _states[i];
  }
  out << "\n";
}

bool Model::load_config(std::string path) {
  std::string file_name = path + "/" + _name + ".txt";
  std::ifstream config_file(file_name);
  if(!config_file.is_open()) {
    throw std::runtime_error("Unable to open file!" + file_name);
    return false;
  }

  Str2Dbl config;

  std::string line;
  while(std::getline(config_file, line)) {
    // k = 10.0
    // mass = 20.0
    auto pos = line.find("=");
    if (pos == std::string::npos) {
      throw std::runtime_error("Wrong formatted line!" + line);
      return false;
    }
    std::string key = line.substr(0, pos);
    std::string value_str = line.substr(pos + 1);

    key = trim(key);
    value_str = trim(value_str);
    
    double value = std::stod(value_str);
    
    config[key] = value;
  }
  config_file.close();
  if(!set_config(config)) {
    throw std::runtime_error("Error setting config");
    return false;
  }
  return true;
}

bool Model::save_config(std::string path) {
  auto maybe_config = get_config();
  if(!maybe_config) {
    return false;
  }
  std::string file_name = path + "/" + _name + ".txt";
  std::ofstream config_file(file_name);
  if(!config_file.is_open()) {
    throw std::runtime_error("Error opening file!" + file_name);
    return false;
  }
  
  // for(const auto &element : config) {}
  for (const auto &[key, value] : maybe_config.value()) {
    config_file << key << " = " << value << "\n";
  }

  config_file.close();
  return true;
}

bool Model::set_config(Str2Dbl config) {
  return true;
}

std::optional<Str2Dbl> Model::get_config() const {
  return {};
}

Vec Model::compute_x_dot(double dt, Vec inputs, Vec states) {
  if(dt <= 0) {
    throw std::invalid_argument("Invalid dt");
  }
  if(inputs.size() != _n_inputs) {
    throw std::invalid_argument("Invalid input sizes");
  }
  return compute_x_dot_impl(dt, inputs, states);
}

void Model::log() {
  // If the file is open (then the logging is enabled).
  if (_log_file.is_open()) {
    csv_row(_log_file);
  }
}