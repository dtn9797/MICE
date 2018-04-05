#include "emporium.h"
#include "controller.h"
#include <iostream>
int main () {
 Emporium em;
 Controller con(em);
 con.cli();
 return 0;
}
