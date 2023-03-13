#include "IpAddress.h"

int main()
{
    IpAddressContainer ipContainer;
    ipContainer.readFromCin();
    ipContainer.sortInvert();
    ipContainer.printAddresses();
    ipContainer.printFilter(IpAddressFilter{ 1 });
    ipContainer.printFilter(IpAddressFilter{ 46, 70 });
    ipContainer.printFilter(IpAddressFilter{ 46, 46, 46, 46, true });
    return 0;
}
