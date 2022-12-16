#include "string"

#ifndef TPMS_PARSER_H
#define TPMS_PARSER_H

namespace TPMS
{
    class Parser
    {
    public:
        static uint32_t readUInt32LE(const std::string buffer, size_t position);
        static uint8_t readUInt8(const std::string buffer, size_t position);
    };
}

#endif
