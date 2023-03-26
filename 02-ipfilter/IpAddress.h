#pragma once

#include <array>
#include <string>
#include <vector>

class IpAddress
{
public:
    enum AddressPart
    {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        PART_COUNT
    };

    explicit IpAddress(std::string&& address);

    [[nodiscard]] uint8_t first() const { return address_[AddressPart::FIRST]; }
    [[nodiscard]] uint8_t second() const { return address_[AddressPart::SECOND]; }
    [[nodiscard]] uint8_t third() const { return address_[AddressPart::THIRD]; }
    [[nodiscard]] uint8_t fourth() const { return address_[AddressPart::FOURTH]; }

    [[nodiscard]] uint8_t part(AddressPart) const;

private:
    std::array<uint8_t, PART_COUNT> address_;

    friend bool operator<(const IpAddress& l, const IpAddress& r);
};

std::ostream& operator<<(std::ostream& out, const IpAddress&);
bool operator<(const IpAddress& l, const IpAddress& r);
bool operator>(const IpAddress& l, const IpAddress& r);

class IpAddressFilter
{
public:
    enum
    {
        NOT_SET = 256
    };

    explicit IpAddressFilter(uint16_t f, uint16_t s = NOT_SET, uint16_t t = NOT_SET, uint16_t fh = NOT_SET, bool oneOf = false);

    [[nodiscard]] bool isMatch(const IpAddress&) const;

private:
    size_t count_;
    bool oneOf_;
    std::array<uint16_t, IpAddress::PART_COUNT> filter_;
};

class IpAddressContainer
{
public:
    void readFromCin();

    void sortInvert();
    void printAddresses();
    void printFilter(const IpAddressFilter& filter);

private:
    std::vector<IpAddress> ipAddress_;
};
