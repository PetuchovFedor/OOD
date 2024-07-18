#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/IInputDataStream.h"
#include "../main/CMemoryInputStream.h"
#include "../main/CFileInputStream.h"
#include "../main/IOutputDataStream.h"
#include "../main/CMemoryOutputStream.h"
#include "../main/CFileOutputStream.h"
#include "../main/CEncryptStream.h"
#include "../main/CDecryptStream.h"
#include "../main/CCompressStream.h"
#include "../main/CDecompressStream.h"
using namespace std;

TEST_CASE("Check input streams")
{
	GIVEN("Memory input stream")
	{
		vector<uint8_t> memory{ 1, 2, 3, 4, 5, 6 };
		CMemoryInputStream stream(memory);
		WHEN("ReadByte()")
		{
			uint8_t byte = stream.ReadByte();
			REQUIRE(byte == memory[0]);
		}
		WHEN("ReadBlock()")
		{
			uint8_t* block = new uint8_t[4];
			auto size = stream.ReadBlock(block, 4);
			REQUIRE(size == 4);
			REQUIRE(block[0] == memory[0]);
			REQUIRE(block[1] == memory[1]);
			REQUIRE(block[2] == memory[2]);
			REQUIRE(block[3] == memory[3]);			
			WHEN("Exception")
			{
				REQUIRE_THROWS_AS(stream.ReadBlock(block, 10), ios_base::failure);
			}
			delete[] block;
		}
		WHEN("IsEOF()")
		{
			uint8_t* block = new uint8_t[6];
			auto size = stream.ReadBlock(block, 6);
			REQUIRE(stream.IsEOF() == true);
			THEN("Exception with eof")
			{
				REQUIRE_THROWS_AS(stream.ReadBlock(block, 10), ios_base::failure);
				REQUIRE_THROWS_AS(stream.ReadByte(), ios_base::failure);
			}
			delete[] block;
		}
	}
	GIVEN("File input stream")
	{
		ifstream inp("inp1.dat");
		CFileInputStream stream("inp.dat");
		char b1; inp.get(b1);
		char b2; inp.get(b2);
		char b3; inp.get(b3);
		char b4; inp.get(b4);
		WHEN("ReadByte()")
		{
			uint8_t byte = stream.ReadByte();
			REQUIRE(byte == static_cast<uint8_t>(b1));
		}
		WHEN("ReadBlock()")
		{
			uint8_t* block = new uint8_t[4];
			auto size = stream.ReadBlock(block, 4);
			REQUIRE(size == 4);
			REQUIRE(block[0] == static_cast<uint8_t>(b1));
			REQUIRE(block[1] == static_cast<uint8_t>(b2));
			REQUIRE(block[2] == static_cast<uint8_t>(b3));
			REQUIRE(block[3] == static_cast<uint8_t>(b4));
			WHEN("Exception")
			{
				REQUIRE_THROWS_AS(stream.ReadBlock(block, 10), ios_base::failure);
			}
			delete[] block;
		}
		WHEN("IsEOF()")
		{
			uint8_t* block = new uint8_t[6];
			auto size = stream.ReadBlock(block, 6);
			stream.ReadByte();
			REQUIRE(stream.IsEOF() == true);
			THEN("Exception with eof")
			{
				REQUIRE_THROWS_AS(stream.ReadBlock(block, 10), ios_base::failure);
				REQUIRE_THROWS_AS(stream.ReadByte(), ios_base::failure);
			}
			delete[] block;
		}
	}
}

TEST_CASE("Check output stream")
{
	GIVEN("Memory output stream")
	{
		vector<uint8_t> memory;
		CMemoryOutputStream stream(memory);
		WHEN("WriteByte()")
		{
			uint8_t b = 1;
			stream.WriteByte(b);
			REQUIRE(memory[0] == b);
		}
		WHEN("WriteBlock()")
		{
			uint8_t* bl = new uint8_t [5];
			bl[0] = 0;
			bl[1] = 1;
			bl[2] = 2;
			bl[3] = 3;
			bl[4] = 4;
			stream.WriteBlock(bl, 5);
			REQUIRE(memory[0] == bl[0]);
			REQUIRE(memory[1] == bl[1]);
			REQUIRE(memory[2] == bl[2]);
			REQUIRE(memory[3] == bl[3]);
			REQUIRE(memory[4] == bl[4]);
			delete[] bl;
			
		}
		WHEN("Exception with close()")
		{
			stream.Close();
			uint8_t b = 1;
			REQUIRE_THROWS_AS(stream.WriteByte(b), logic_error);
			uint8_t* bl = new uint8_t[5];
			bl[0] = 0;
			bl[1] = 1;
			bl[2] = 2;
			bl[3] = 3;
			bl[4] = 4;
			REQUIRE_THROWS_AS(stream.WriteBlock(bl, 5), logic_error);
			delete[] bl;
		}
	}
}

TEST_CASE("Check decorators")
{
	//using 
	GIVEN("Input and output memory stream")
	{
		vector<uint8_t> memory1{ 1, 2, 3, 4, 5, 6 };
		vector<uint8_t> memory2;
		unique_ptr<IOutputDataStream> output = make_unique< CMemoryOutputStream>(memory2);
		WHEN("Check encrypt and decrypt")
		{
			output = make_unique<CEncryptStream>(move(output), 3);
			uint8_t b1 = 1;
			uint8_t b2 = 2;
			uint8_t b3 = 3;
			output->WriteByte(b1);
			output->WriteByte(b2);
			output->WriteByte(b3);
			unique_ptr<IInputDataStream> input = make_unique< CMemoryInputStream>(memory2);
			input = make_unique<CDecryptStream>(move(input), 3);
			REQUIRE(input->ReadByte() == b1);
			REQUIRE(input->ReadByte() == b2);
			REQUIRE(input->ReadByte() == b3);
		}
		WHEN("Compress and decompress")
		{
			//через std::string
			output = make_unique<CCompressStream>(move(output));
			auto str = "ssssssfff3";
			string str1;
			//for (auto i = 0; i < 500; i)
			output->WriteBlock(str, 10);
			unique_ptr<IInputDataStream> input = make_unique< CMemoryInputStream>(memory2);
			input = make_unique<CDecompressStream>(move(input));
			char* s = new char[11];
			input->ReadBlock(s, 10);
			s[10] = '\0';
			REQUIRE(strcmp(s, str) == 0);
		}
	}
}