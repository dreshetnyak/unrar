#ifndef _RAR_FILE_VECTOR_
#define _RAR_FILE_VECTOR_

#include "file.hpp"

// Windows provides us the files as a byte streams, usually we read those streams and place them in RAM in a vector, this vector is provided to our parser, in a case of RAR the UnRar
// library is made in a such way that it accepts the RAR file name and then it itself opens the file and read it, obviously we can't do that. So analyzing the library code I found that
// A rar archive is represented by the class Archive, which is derived from the class File which manages the work with files and it got the virtual functions to override. So here we
// derive from this class and replace the work with file to with the work with the byte vector. In that case the change that need to be done to the UnRar lib will be minimal - just to
// replace the class from which Archive is derived from. At least this is the intent.
// RAROpenArchiveEx returns DataSet, which contains Archive Arc, which is derived from File.

//In archive.hpp
//Added: #include "file_vector.hpp"
//Changed: "class Archive:public File" to "class Archive:public FileVector"

class FileVector : public File
{
	const std::vector<char>* FileContent = nullptr;
	int64_t CurrentOffset = 0;

public:
	FileVector() = default;
	FileVector(const FileVector& fileVector) = delete;
	FileVector(FileVector&& fileVector) = delete;
	~FileVector() override = default;
	bool Open(const wchar* name, uint mode) override;
	bool Close() override;
	int Read(void* data, size_t size) override;
	void Seek(int64 offset, int method) override;
	int64 Tell() override;
	bool IsOpened() override;

	void SetFileContent(const std::vector<char>& fileContent) { FileContent = &fileContent; }
};

#endif