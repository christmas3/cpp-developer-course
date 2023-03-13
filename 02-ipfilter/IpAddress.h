#pragma once

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
        FOURTH
    };

    explicit IpAddress(std::string&& address);

    [[nodiscard]] int first() const { return address_[AddressPart::FIRST]; }
    [[nodiscard]] int second() const { return address_[AddressPart::SECOND]; }
    [[nodiscard]] int third() const { return address_[AddressPart::THIRD]; }
    [[nodiscard]] int fourth() const { return address_[AddressPart::FOURTH]; }

    [[nodiscard]] int part(AddressPart) const;
protected:
    IpAddress(uint16_t f, uint16_t s, uint16_t t, uint16_t fh);

private:
    int address_[FOURTH + 1];
};

std::ostream& operator<<(std::ostream& out, const IpAddress&);
bool operator<(const IpAddress& l, const IpAddress& r);
bool operator>(const IpAddress& l, const IpAddress& r);

class IpAddressFilter : private IpAddress
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
