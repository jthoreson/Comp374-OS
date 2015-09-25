#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "time.h"
#include "time.h"
#include "windows.h"
#include "winbase.h"

using namespace std;

void __cdecl _tmain(int argc, TCHAR *argv[])
{
	clock_t start, end;                 //intializing variables for the clock function
	int pause;

	DWORD totalBytes = 0;               //setting total bytes to 0 to intialize it
	DWORD BytesRead;              //variable for how many bytes have been read per iteration
	long buffSize;                      //this is chosen my the user to set the buffer size
	buffSize = _tcstol(argv[1], NULL, 10);

	char   * readBuffer = new char[buffSize];
	HANDLE openFile, writeFile;
	openFile = CreateFile(argv[2], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	writeFile = CreateFile(argv[3], GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BOOL endOfFile = TRUE;							//runs clock until end of file
	start = clock();
	while (endOfFile != FALSE)						//loop that keeps reading bytes until bytes read = 0
	{
		ReadFile(openFile, readBuffer, buffSize, &BytesRead, NULL);
		totalBytes += BytesRead;
		endOfFile = (BytesRead > 0);
		if (endOfFile == TRUE)						//once it is done it writes the file
		{
			WriteFile(writeFile, readBuffer, BytesRead, NULL, NULL);
		}
	}
	end = clock();
	double totalTime = static_cast<double>(end - start) / CLOCKS_PER_SEC; //turns time into double
	cout << "Copied bytes: " << totalBytes << " in: " << totalTime << " seconds " <<
	 " at the rate of: " << static_cast<double>(totalBytes) / totalTime << " bytes per second." << " Buffer size is: " << buffSize << std::endl;

	CloseHandle(openFile);							//prints buffersize, how long it took to copy and how many bytes per second
	CloseHandle(writeFile);
	delete[] readBuffer;
}




