#include "view/facade.h"

int main() {
  const s21::Facade& window = s21::Facade::GetInstance();
  window.Run();
  return 0;
}
