#include "rar.hpp"
#include "file_vector.hpp"

bool FileVector::Open(const wchar* name, uint mode)
{
	return true;
}

bool FileVector::Close()
{
	FileContent = nullptr;
	CurrentOffset = 0;
	return true;
}

int FileVector::Read(void* data, const size_t size)
{
	if (FileContent == nullptr)
		return 0;
	const auto fileSize = FileContent->size();
	const auto bytesToRead = CurrentOffset + size > fileSize
		? fileSize - CurrentOffset
		: size;
	memcpy(data, FileContent->data(), bytesToRead);
	CurrentOffset += static_cast<int64_t>(size);
	return static_cast<int>(bytesToRead);
}

void FileVector::Seek(const int64 offset, const int method)
{
	if (FileContent == nullptr)
		return;

	switch (method)
	{
	case SEEK_SET: // Beginning of the file
		CurrentOffset = offset;
		break;
	case SEEK_CUR: // Current position in the file
		CurrentOffset += offset;
		break;
	case SEEK_END: // End of the file
		CurrentOffset = FileContent != nullptr ? static_cast<int64_t>(FileContent->size()) : 0;
		break;
	default:
		break;
	}
}

int64 FileVector::Tell()
{
	return CurrentOffset;
}

bool FileVector::IsOpened()
{
	return FileContent != nullptr;
}