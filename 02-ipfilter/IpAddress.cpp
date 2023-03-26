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
        if (i < PART_COUNT) {
            address_[i] = std::stoi(num);
        }
        else {
            throw std::logic_error("error format ip address");
        }
    }
}

std::ostream& operator<<(std::ostream& out, const IpAddress& address)
{
    return out << (uint16_t)address.first() << '.' << (uint16_t)address.second() << '.' << (uint16_t)address.third() << '.' << (uint16_t)address.fourth();
}

bool operator<(const IpAddress& l, const IpAddress& r)
{
    return l.address_ < r.address_;
}

bool operator>(const IpAddress& l, const IpAddress& r)
{
    return r < l;
}

uint8_t IpAddress::part(IpAddress::AddressPart p) const
{
    return address_[p];
}

IpAddressFilter::IpAddressFilter(uint16_t f, uint16_t s, uint16_t t, uint16_t fh, bool oneOf)
    : count_(IpAddress::PART_COUNT)
    , oneOf_(oneOf)
    , filter_{ f, s, t, fh }
{
    for (size_t i = 0; i < IpAddress::PART_COUNT; ++i) {
        if (NOT_SET == filter_[i]) {
            --count_;
        }
    }
}

bool IpAddressFilter::isMatch(const IpAddress& address) const
{
    for (size_t i = 0; i < count_; ++i) {
        auto p = static_cast<IpAddress::AddressPart>(i);
        if (address.part(p) != filter_[i]) {
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
