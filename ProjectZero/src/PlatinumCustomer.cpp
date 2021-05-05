#include "PlatinumCustomer.h"

PlatinumCustomer::PlatinumCustomer(std::string fn, std::string ln, std::string gid, float as, float bb)
{
   Customer::Customer(fn, ln, gid, as);
   bonusBucks = bb;
   //ctor
}

PlatinumCustomer::~PlatinumCustomer()
{
   //dtor
}
