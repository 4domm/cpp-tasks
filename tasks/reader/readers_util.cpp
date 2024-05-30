#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}
size_t LimitReader::Read(char *buf, size_t len) {
    if (limit_ == 0) {
        return 0;
    }
    size_t to_read = std::min(len, limit_);
    size_t bytes_read = reader_->Read(buf, to_read);
    limit_ -= bytes_read;
    return bytes_read;
}
TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}
size_t TeeReader::Read(char *buf, size_t len) {
    size_t total_bytes_read = 0;
    for (const auto &reader : readers_) {
        current_ = reader->Read(buf + total_bytes_read, len - total_bytes_read);
        total_bytes_read += current_;
        if (total_bytes_read >= len) {
            break;
        }
    }
    return total_bytes_read;
}
char HexToChar(char hexchar) {
    const int32_t ten = 10;
    return (hexchar >= 'a') ? static_cast<char>(hexchar - 'a' + ten) : static_cast<char>(hexchar - '0');
}
HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}
size_t HexDecodingReader::Read(char *buf, size_t len) {
    size_t hex_len = len * 2;
    const int32_t hexadecimal = 16;
    char *buffer = new char[hex_len];
    size_t readed = reader_->Read(buffer, hex_len);
    for (size_t i = 0; i < readed; i += 2) {
        char *ptr = buffer + i;
        buf[i / 2] = static_cast<char>(HexToChar(ptr[0]) * hexadecimal + HexToChar(ptr[1]));
    }
    delete[] buffer;
    return readed / 2;
}
