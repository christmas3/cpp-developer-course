#include "IpAddress.h"

#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>

IpAddress::IpAddress(std::string&& address)
    : address_{}
{
    std::istringstream strStream(std::move(address));
    int i = 0;
    for (std::string num; std::getline(strStream, num, '.'); ++i) {
        if (i <= FOURTH) {
            address_[i] = std::stoi(num);
        }
        else {
            throw std::logic_error("error format ip address");
        }
    }
}

std::ostream& operator<<(std::ostream& out, const IpAddress& address)
{
    return out << address.first() << '.' << address.second() << '.' << address.third() << '.' << address.fourth();
}

bool operator<(const IpAddress& l, const IpAddress& r)
{
    if (l.first() < r.first()) {
        return true;
    }
    if (l.first() == r.first()) {
        if (l.second() < r.second()) {
            return true;
        }
        if (l.second() == r.second()) {
            if (l.third() < r.third()) {
                return true;
            }
            if (l.third() == r.third()) {
                return l.fourth() < r.fourth();
            }
        }
    }

    return false;
}

bool operator>(const IpAddress& l, const IpAddress& r)
{
    return r < l;
}

IpAddress::IpAddress(uint16_t f, uint16_t s, uint16_t t, uint16_t fh)
    : address_{ f, s, t, fh }
{
}

int IpAddress::part(IpAddress::AddressPart p) const
{
    return address_[p];
}

IpAddressFilter::IpAddressFilter(uint16_t f, uint16_t s, uint16_t t, uint16_t fh, bool oneOf)
    : IpAddress(f, s, t, fh)
    , count_(AddressPart::FOURTH + 1)
    , oneOf_(oneOf)
{
    for (size_t i = 0; i <= AddressPart::FOURTH; ++i) {
        if (NOT_SET == part(static_cast<AddressPart>(i))) {
            --count_;
        }
    }
}

bool IpAddressFilter::isMatch(const IpAddress& address) const
{
    for (size_t i = 0; i < count_; ++i) {
        auto p = static_cast<AddressPart>(i);
        if (address.part(p) != part(p)) {
            if (!oneOf_) {
                return false;
            }
        }
        else if (oneOf_) {
            return true;
        }
    }

    return !oneOf_;
}

void IpAddressContainer::readFromCin()
{
    for (std::string line; std::getline(std::cin, line);) {
        std::istringstream strStream(std::move(line));
        std::getline(strStream, line, '\t');
        try {
            ipAddress_.emplace_back(std::move(line));
        }
        catch (std::exception& e) {
            std::cerr << "parse ip address error: " << e.what() << std::endl;
        }
    }
}

void IpAddressContainer::sortInvert()
{
    std::sort(ipAddress_.begin(), ipAddress_.end(), std::greater());
}

void IpAddressContainer::printAddresses()
{
    std::copy(ipAddress_.begin(), ipAddress_.end(), std::ostream_iterator<IpAddress>(std::cout, "\n"));
}

void IpAddressContainer::printFilter(const IpAddressFilter& filter)
{
    std::copy_if(ipAddress_.begin(),
                 ipAddress_.end(),
                 std::ostream_iterator<IpAddress>(std::cout, "\n"),
                 std::bind(&IpAddressFilter::isMatch, &filter, std::placeholders::_1));
}
