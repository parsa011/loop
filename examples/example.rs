import Standard.Console;

struct Animal {
  string Name,
  u8 Age
}

struct Cat : Animal {
  byte Color; // or in future Hex

  fn Sound() {
    Console.Writeln('Meaow');
  }
}


fn Main(u8 param1, string param2) {
  Cat myCat;
  myCat.Sound();
}