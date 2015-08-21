
/**
 * \file tStream.cpp
 * \date 2015
 */

#include "unittest.hpp"

#include <mtarcommon/stream.hpp>

#include <cstring>

const char NAME_UTF8[] = {
    0xEF, 0xBC, 0xAE, 0xEF, 0xBD, 0x81, 0xEF, 0xBD, 0x8D, 0xEF, 0xBD, 0x85, 0xE3, 0x80, 0x80, 0xEF, 0xBD, 
    0x97, 0xEF, 0xBD, 0x89, 0xEF, 0xBD, 0x94, 0xEF, 0xBD, 0x88, 0xE3, 0x80, 0x80, 0xEF, 0xBD, 0x93, 0xEF,
    0xBD, 0x90, 0xEF, 0xBD, 0x81, 0xEF, 0xBD, 0x83, 0xEF, 0xBD, 0x85, 0xEF, 0xBD, 0x93, 0x00 };


CPP_TEST( i18n )
{
    mtar::path p;
    {
        std::string utf8name(NAME_UTF8);
        p = mtar::create_path(utf8name + ".txt");
    }
    {
        mtar::ostream ostrm(p);
        ostrm.write("foobar\n", 7);
    }
    {
        mtar::istream istrm(p);
        char BUFF[8];
        istrm.read(BUFF, 7);
        BUFF[7] = '\0';
        TEST_TRUE( strcmp(BUFF, "foobar\n") == 0 );
    }
    {
        mtar::ostream ostrm(PATH_LIT("copyFile.txt"));
        mtar::istream istrm(p);
        mtar::stream_copy(ostrm, istrm, 7);
    }
    {
        mtar::istream istrm(PATH_LIT("copyFile.txt"));
        char BUFF[8];
        istrm.read(BUFF, 7);
        BUFF[7] = '\0';
        TEST_TRUE(strcmp(BUFF, "foobar\n") == 0);
    }
}
