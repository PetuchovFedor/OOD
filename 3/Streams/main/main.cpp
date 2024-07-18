#include <iostream>
#include "CCompressStream.h"
#include "CDecompressStream.h"
#include "CDecryptStream.h"
#include "CEncryptStream.h"
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include <sstream>
#include "CMemoryInputStream.h"
#include "CMemoryOutputStream.h"
using namespace std;


void HandleOutputStreamOption(unique_ptr<IOutputDataStream>& output,
	/*istream& args*/const string& option, unsigned seed = 0)
{
	if (option == "--encrypt")
	{
		output = make_unique<CEncryptStream>(move(output), seed);
	}
	else if (option == "--compress")
	{
		output = make_unique<CCompressStream>(move(output));
	}
}

void HandleInputStreamOption(unique_ptr<IInputDataStream>& input,
	/*istream& args*/ const string& option, unsigned seed = 0)
{
	if (option == "--decrypt")
	{
		input = make_unique<CDecryptStream>(move(input), seed);
	}
	else if (option == "--decompress")
	{
		input = make_unique<CDecompressStream>(move(input));
	}
}
void HandleOption(unique_ptr<IInputDataStream>& input, unique_ptr<IOutputDataStream>& output,
	istream& args)
{
	string option;
	args >> option;
	if (option.find("crypt") != string::npos)
	{
		unsigned seed;
		args >> seed;
		if (option == "--decrypt")
		{
			input = make_unique<CDecryptStream>(move(input), seed);
		}
		else if (option == "--encrypt")
		{
			output = make_unique<CEncryptStream>(move(output), seed);
		}
	}	
	else if (option == "--compress")
	{
		output = make_unique<CCompressStream>(move(output));
	}
	else if (option == "--decompress")
	{
		input = make_unique<CDecompressStream>(move(input));
	}
}

void PrintFromTo(unique_ptr<IInputDataStream>& from, unique_ptr<IOutputDataStream>& to)
{
	while (!from->IsEOF())
	{
		to->WriteByte(from->ReadByte());
	}
}

int main(int argc, char* argv[])
{
	vector<string> args(argv + 1, argv + argc - 2);
	unique_ptr<IInputDataStream> input = make_unique< CFileInputStream>(argv[argc - 2]);
	unique_ptr<IOutputDataStream> output = make_unique< CFileOutputStream>(argv[argc - 1]);
	int idx = 0;
	while (idx != args.size())
	{
		if (args[idx] == "--encrypt")
		{
			auto it = find(args.begin(), args.end(), "--decompress"s);
			int j;
			it == args.end() ? j = args.size() :
				 j = distance(args.begin() + idx, it);
			for (int i = (j - 1); i > (idx - 1); i--)
			{
				if (args[i] == "--encrypt" || args[i] == "--compress")
				{
					unsigned seed = 0;
					if (args[i] == "--encrypt")
					{
						try
						{
							seed = stoi(args[i + 1]);
						}
						catch (...)
						{
							cout << "Error with entering key" << endl;
							continue;
						}
					}
					HandleOutputStreamOption(output, args[i], seed);
				}
			}
			idx = j;
		}
		else if (args[idx] == "--decompress"s)
		{
			auto it = find(args.begin(), args.end(), "--encrypt"s);
			int j;
			it == args.end() ? j = args.size() :
				j = distance(args.begin() + idx, it);
			for (auto i = idx; i < j; i++)
			{
				if (args[i] == "--decrypt" || args[i] == "--decompress")
				{
					unsigned seed = 0;
					if (args[i] == "--decrypt")
					{
						try
						{
							seed = stoi(args[i + 1]);
						}
						catch (...)
						{
							cout << "Error with entering key" << endl;
							continue;
						}
					}
					HandleInputStreamOption(input, args[i], seed);
				}
			}
			idx = j;
		}
		
	}
	//int begin, end;
	//if (args[0] == "--decompress")
	//{
	//	begin = 0;
	//	end = args.size();
	//}
	//else if (args[0] == "--encrypt")
	//{
	//	begin = args.size() - 1;
	//	end = -1;
	//}
	//else
	//{
	//	cout << "Error with first option" << endl;
	//	return 1;
	//}
	//for (int i = 0; i < args.size(); i++)
	////for (int i = args.size() - 1; i > -1; i--)
	//{
	//	unsigned seed = 0;
	//	if (args[i].find("crypt") != string::npos)
	//		//args[i] += ' ' + args[i + 1];
	//	{
	//		try
	//		{
	//			seed = stoi(args[i + 1]);
	//		}
	//		catch (...)
	//		{
	//			cout << "Error with entering key" << endl;
	//		}
	//	}
	//	//stringstream stream(args[i]);
	//	
	//	if (args[i] == "--decrypt" || args[i] == "--decompress")
	//	{
	//		HandleInputStreamOption(input, args[i], seed);
	//	}
	//	//HandleOption(input, output, stream);
	//}
	try
	{
		PrintFromTo(input, output);
	}
	catch (...)
	{
		output->Close();
	}
}