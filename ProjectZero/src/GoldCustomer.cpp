#include "GoldCustomer.h"

GoldCustomer::GoldCustomer(std::string fn, std::string ln, std::string gid, float as, float dp)
{
   Customer::Customer(fn, ln, gid, as);
   discountPercentage = dp;
   //ctor
}

GoldCustomer::~GoldCustomer()
{
   //dtor
}
