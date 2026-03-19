#include <string>
#include <iostream>
#include <vector>



// In una classe, di default, gli elementi interni sono privati, non modificabili quindi esternamente. Per poterlo fare dobbiamo aggiungere la dicitura Pubblic.
class Point
{
private:
  std::string name = "undefined";
  double z;
public:
  double x = 0.0;
  double y{0.0};

  Point() = default;

  Point(std::string name, double x, double y); // E' una funzione senza tipo di ritorno per creare l'oggetto di tipo Point

  void place(double x, double y, double z);

  void print();

  void set_name(std::string name)
  {
    this->name = name;
  }
};






int main()
{

  Point p0;
  Point p1("P1", 1.0, 1.0);
  Point p2("P2", -1.0, -1.0);

  std::cout << p1.x << ", " << p1.y << std::endl;
  // std::cout << p2.x << ", " << p2.y << std::endl; //Non molto bello da fare


  p1.set_name("first point");
  p1.print();
  p2.print();
  
  p0.place(0,0,0);
  p0.print();

  std::vector<int> vecInt; //Proprietà specifiche per gli interi
  vecInt.push_back(0); //
  vecInt.push_back(1);
  vecInt.push_back(2); 
  //Altro modo per fare un vettore: 
  std::vector<int> vecInt2({5,9,7});


  //La variabile size_t viene normalmente utilizzata per salvare la dimensione di vettori o di elementi.
  for (size_t i = 0; i < vecInt2.size(); i++)
  {
    std::cout << "index: {" << i << "}: " << vecInt2[i] << std::endl;
  }



  std::vector<Point> points(4);
  std::vector<Point> points2(4, Point("-", 1.0,4.0)); //Un altro modo di creare un vettore riutilizzando la nostra struttura.

  
  
  for (size_t i = 0; i < points2.size(); i++)
  {
    points2[i].set_name("#" + std::to_string(i));
    points2[i].print();
  }
  

  //Per fare un for per tutti gli elementi dell'elemento points2:
  std::cout << "Second for-----" << std::endl;
  for(Point element : points2 ){
    element.place(0,0,0);
    element.print();    
  }
  //Come possiamo vedere, il successivo for non stampa quello che ci aspetteremmo, questo è dato perchè abbiamo fatto una sostituzione su di una variabile "usa e getta" chiamata "element". Per questo motivo l'element non modifica effettivamente la variabile points2. Questa cosa era implicita nella scrittura: "Point element:points2"
  std::cout << "Third for-----" << std::endl;
  for(Point element : points2 ){
    element.print();    
  }
  
  std::cout << "==========" << std::endl;
  for(Point &element : points2 ){
    element.place(10,10,10);
    element.print();    
  }

  return 0;
}

void Point::print()
{
  std::cout << name << ": " << x << ", " << this->y << std::endl;
}

Point::Point(std::string name, double x, double y)
{
  /*Instead of
  this->name = name;
  
  We can use:  
  */
  this->set_name(name);

  /*Instead of
  this->x = x;
  this->y = y;
  
  We can use:  
  */
  this->place(x,y, 0.0);

}

//Non importa se prima avessimo scritto "x" e adesso "new_x", importante è che i tipi delle variabili siano gli stessi
void Point::place(double new_x, double new_y, double new_z){
  x = new_x;
  y = new_y;
  z = new_z;
}