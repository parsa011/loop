import Std.Console;

struct Animal {
  string Name,
  u8 Age
}

struct Cat : Animal {
  byte Color;
  fn Sound() {
    Console.Writeln('Meaow');
  }
}

fn Main() {
  Cat myCat;
  myCat.Sound();
}