#include "view/facade.h"

int main() {
  const Facade& window = Facade::GetInstance();
  window.Run();
  return 0;
}
