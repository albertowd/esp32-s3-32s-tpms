#include "TPMSParser.h"

uint32_t TPMS::Parser::readUInt32LE(const std::string buffer, size_t position)
{
    return TPMS::Parser::readUInt8(buffer, position) |
           TPMS::Parser::readUInt8(buffer, position + 1) << 8 |
           TPMS::Parser::readUInt8(buffer, position + 2) << 16 |
           TPMS::Parser::readUInt8(buffer, position + 3) << 24;
}

uint8_t TPMS::Parser::readUInt8(const std::string buffer, size_t position)
{
    int offset(position * 2);
    char *restStr;
    if (offset + 2 <= buffer.length())
    {
        return strtoul(buffer.substr(offset, 2).c_str(), &restStr, 16);
    }
    else
    {
        return 0U;
    }
}
