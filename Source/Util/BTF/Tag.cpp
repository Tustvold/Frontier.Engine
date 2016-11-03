#include "Tag.h"
#include <cstdarg>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>


static inline int little_endian() {
	uint16_t t = 0x0001;
	char *c = (char *) &t;
	return *c == 0x01;
}

static inline void *swap_bytes(void *s, size_t len) {
	for (char *b = (char *) s,
				 *e = b + len - 1;
		 b < e;
		 b++, e--) {
		char t = *b;

		*b = *e;
		*e = t;
	}

	return s;
}

static inline void *be2ne(void *s, size_t len) {
	//Big endian
	//return little_endian() ? swap_bytes(s, len) : s;

	//little endian
	return little_endian() ? s : swap_bytes(s, len);
}

void readInt8(CompressionBuffer *buffer, int8_t *output) {
	memcpy(output, be2ne(buffer->readBytes(1),1), 1);
}

void readChar(CompressionBuffer *buffer, char *output) {
	memcpy(output, be2ne(buffer->readBytes(1),1), 1);
}

void readUInt8(CompressionBuffer *buffer, uint8_t *output) {
	memcpy(output, be2ne(buffer->readBytes(1),1), 1);
}

void readInt16(CompressionBuffer *buffer, int16_t *output) {
	memcpy(output, be2ne(buffer->readBytes(2),2), 2);
}

void readUInt16(CompressionBuffer *buffer, uint16_t *output) {
	memcpy(output, be2ne(buffer->readBytes(2),2), 2);
}

void readInt32(CompressionBuffer *buffer, int32_t *output) {
	memcpy(output, be2ne(buffer->readBytes(4),4), 4);
}

void readUInt32(CompressionBuffer *buffer, uint32_t *output){
	memcpy(output, be2ne(buffer->readBytes(4),4), 4);
}

void readFloat(CompressionBuffer *buffer, float *output) {
	memcpy(output, be2ne(buffer->readBytes(4),4), 4);
}

Tag::Tag(uint8_t _type) {
	type = _type;
	listed = false;
	//identifier = 0;
	switch (_type) {
		case TAG_Byte:
			payload_byte = 0;
			break;
		case TAG_Int16:
			payload_short = 0;
			break;
		case TAG_Int32:
			payload_int = 0;
			break;
		case TAG_Float:
			payload_float = 0;
			break;
		case TAG_Byte_Array:
			payload_byteArray = new tagByteArrayData();
			break;
		case TAG_String:
			payload_string = new tagStringData();
			break;
		case TAG_List:
			payload_tagList = new tagListData();
			break;
		case TAG_Compound:
			payload_tagCompound = new tagCompoundData();
			break;
		case TAG_UByte:
			payload_ubyte = 0;
			break;
		case TAG_UInt32:
			payload_uint = 0;
			break;
		default:
			FTAssert(false, "Unrecognised Tag Type");
	}
}

Tag::Tag(CompressionBuffer *buffer, uint8_t _type) {
	if (_type == 0)
		readUInt8(buffer, &_type);
	type = _type;
	listed = false;

	switch (type) {
		case TAG_Byte:
		{
			readInt8(buffer, &payload_byte);
			break;
		}
		case TAG_Int16:
		{
			readInt16(buffer, &payload_short);
			break;
		}
		case TAG_Int32:
		{
			readInt32(buffer, &payload_int);
			break;
		}
		case TAG_Float:
		{
			readFloat(buffer, &payload_float);
			break;
		}
		case TAG_Byte_Array: {
			payload_byteArray = new tagByteArrayData();
			uint32_t len;
			readUInt32(buffer, &len);
            payload_byteArray->data.resize(len);
			for (uint32_t i = 0; i < len; i++) {
				readUInt8(buffer, &payload_byteArray->data[i]);
			}
			break;
		}
		case TAG_String: {
            uint8_t len;
            readUInt8(buffer, &len);
            payload_string = new tagStringData(len);

            for (uint8_t i = 0; i < len; i++) {
				readChar(buffer, &payload_string->data[i]);
			}
            break;
		}
		case TAG_List: {
			payload_tagList = new tagListData();
			uint8_t dataType;
			readUInt8(buffer, &dataType);
			uint16_t len;
			readUInt16(buffer, &len);
			for (uint16_t i = 0; i < len; i++) {
				payload_tagList->addTag(std::make_unique<Tag>(buffer, dataType));
			}
			break;
		}
		case TAG_Compound: {
			payload_tagCompound = new tagCompoundData();
			while (true) {
				uint8_t dataType;
				readUInt8(buffer, &dataType);
				if (dataType == TAG_End)
					break;
				Tag *tag = new Tag(buffer, dataType);
				uint16_t identifier;
				readUInt16(buffer, &identifier);
				payload_tagCompound->addTag(std::unique_ptr<Tag>(tag), identifier);
			}
			break;
		}
		case TAG_UByte:
			readUInt8(buffer, &payload_ubyte);
			break;
        case TAG_UInt32:
            readUInt32(buffer, &payload_uint);
            break;
		default:
			FTAssert(false, "Unrecognised Tag Type");
	}
}

void Tag::writeToBuffer(CompressionBuffer *buffer) {
	if (!listed)
		buffer->buffer_append(be2ne(&type, 1), 1);
	switch (type) {
		case TAG_Byte:
			buffer->buffer_append(be2ne(&payload_byte, 1), 1);
			break;
		case TAG_Int16:
			buffer->buffer_append(be2ne(&payload_short, 2), 2);
			break;
		case TAG_Int32:
			buffer->buffer_append(be2ne(&payload_int, 4), 4);
			break;
		case TAG_Float:
			buffer->buffer_append(be2ne(&payload_float, 4), 4);
			break;
		case TAG_Byte_Array: {
			uint32_t len = (uint32_t)payload_byteArray->data.size();
			buffer->buffer_append(be2ne(&len, 4), 4);
			for (uint32_t i = 0; i < len; i++) {
				char character = payload_byteArray->data[i];
				buffer->buffer_append(be2ne(&character, 1), 1);
			}

			break;
		}
		case TAG_String: {
			uint8_t len = (uint8_t )payload_string->data.size();
			buffer->buffer_append(be2ne(&len, 1), 1);
			for (int i = 0; i < len; i++) {
				char character = payload_string->data[i];
				buffer->buffer_append(be2ne(&character, 1), 1);
			}
			break;
		}
		case TAG_List: {
			uint8_t type = payload_tagList->dataType;
			uint16_t len = (uint16_t)payload_tagList->data.size();

			buffer->buffer_append(be2ne(&type, 1), 1);
			buffer->buffer_append(be2ne(&len, 2), 2);
			for (auto it = payload_tagList->data.begin(); it != payload_tagList->data.end(); ++it) {
                (*it)->writeToBuffer(buffer);
			}

			break;
		}
		case TAG_Compound: {
			for (auto it = payload_tagCompound->data.begin(); it != payload_tagCompound->data.end(); ++it) {
				it->second->writeToBuffer(buffer);
                uint16_t cpy = it->first;
				buffer->buffer_append(be2ne(&cpy, 2), 2);
			}
			unsigned char tagEnd = Tag::TAG_End;
			buffer->buffer_append(be2ne(&tagEnd, 1), 1);
			break;
		}
		case TAG_UByte:
			buffer->buffer_append(be2ne(&payload_ubyte, 1), 1);
			break;
        case TAG_UInt32:
            buffer->buffer_append(be2ne(&payload_uint, 4), 4);
            break;
		default:
			FTAssert(false, "Unrecognised Tag Type");
	}
}

void Tag::logStructure(std::stringstream& ss, uint16_t indent) {
    const char* tabString = "	 ";
	for (int i = 0; i < indent; i++) {
		ss << tabString;
	}
	indent++;
	
	switch (type) {
		case TAG_Byte: {
			ss << "TAG_Byte: " << (unsigned int)this->payload_byte << std::endl;
			break;
		}
		case TAG_Int16: {
			ss << "TAG_Int16: " << (unsigned int)this->payload_short << std::endl;
			break;
		}
		case TAG_Int32: {
			ss << "TAG_Int32: " << this->payload_int << std::endl;
			break;
		}
		case TAG_Float: {
			ss << "TAG_Float: " << this->payload_float << std::endl;
			break;
		}
		case TAG_Byte_Array: {
			ss << "TAG_ByteArray: " << payload_byteArray->data.size() << std::endl;
			//for (int i = 0; i < payload_byteArray->data.size(); i++) {
            //    for (int i = 0; i < indent; i++) {
            //        ss << tabString;
            //    }
            //    ss << (unsigned int)payload_byteArray->data[i] << std::endl;
			//}
			break;
		}
		case TAG_String: {
			ss << "TAG_String: " << payload_string->data << std::endl;
			break;
		}
		case TAG_List: {
			ss << "TAG_List: " << payload_tagList->data.size() << std::endl;
			for (auto it = payload_tagList->data.begin(); it != payload_tagList->data.end(); ++it) {
                (*it)->logStructure(ss, indent);
			}
			break;
		}
		case TAG_Compound: {
            ss << "TAG_Compound:" << std::endl;

            // We sort the output as this makes the output deterministic allowing trivial comparison
            std::vector<std::pair<uint16_t, Tag*>> sorted;

			for (const auto& it : payload_tagCompound->data) {
                sorted.push_back(std::make_pair(it.first, it.second.get()));
			}

            std::sort(sorted.begin(), sorted.end(), [](const std::pair<uint16_t, Tag*>&a, const std::pair<uint16_t, Tag*>&b) {
                return std::less<uint16_t>()(a.first, b.first);
            });

            for (auto it : sorted) {
                for (int i = 0; i < indent; i++) {
                    ss << tabString;
                }
                ss << "Key: " << it.first << std::endl;
                it.second->logStructure(ss, indent);
            }

			break;
		}
		case TAG_UByte: {
			ss << "TAG_UByte: " << (unsigned int)payload_ubyte << std::endl;
			break;
		}
        case TAG_UInt32: {
            ss << "TAG_UInt32: " << payload_uint << std::endl;
            break;
        }
		default:
			FTAssert(false, "Unrecognised Tag Type");
	}
}





