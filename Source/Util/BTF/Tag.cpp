#include "Tag.h"
#include <cstdarg>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>

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
		buffer->read<uint8_t>(&_type);
	type = _type;
	listed = false;

	switch (type) {
		case TAG_Byte:
		{
			buffer->read(&payload_byte);
			break;
		}
		case TAG_Int16:
		{
			buffer->read(&payload_short);
			break;
		}
		case TAG_Int32:
		{
			buffer->read(&payload_int);
			break;
		}
		case TAG_Float:
		{
			buffer->read(&payload_float);
			break;
		}
		case TAG_Byte_Array: {
			payload_byteArray = new tagByteArrayData();
			uint32_t len;
			buffer->read(&len);
            payload_byteArray->data.resize(len);
			for (uint32_t i = 0; i < len; i++) {
				buffer->read(&payload_byteArray->data[i]);
			}
			break;
		}
		case TAG_String: {
            uint8_t len;
            buffer->read(&len);
            payload_string = new tagStringData(len);

            for (uint8_t i = 0; i < len; i++) {
				buffer->read(&payload_string->data[i]);
			}
            break;
		}
		case TAG_List: {
			payload_tagList = new tagListData();
			uint8_t dataType;
			buffer->read(&dataType);
			uint16_t len;
			buffer->read(&len);
			for (uint16_t i = 0; i < len; i++) {
				payload_tagList->addTag(std::make_unique<Tag>(buffer, dataType));
			}
			break;
		}
		case TAG_Compound: {
			payload_tagCompound = new tagCompoundData();
			while (true) {
				uint8_t dataType;
				buffer->read(&dataType);
				if (dataType == TAG_End)
					break;
				Tag *tag = new Tag(buffer, dataType);
				uint16_t identifier;
				buffer->read(&identifier);
				payload_tagCompound->addTag(std::unique_ptr<Tag>(tag), identifier);
			}
			break;
		}
		case TAG_UByte:
			buffer->read(&payload_ubyte);
			break;
        case TAG_UInt32:
            buffer->read(&payload_uint);
            break;
		default:
			FTAssert(false, "Unrecognised Tag Type");
	}
}

void Tag::writeToBuffer(CompressionBuffer *buffer) {
	if (!listed)
		buffer->write(&type);
	switch (type) {
		case TAG_Byte:
			buffer->write(&payload_byte);
			break;
		case TAG_Int16:
			buffer->write(&payload_short);
			break;
		case TAG_Int32:
			buffer->write(&payload_int);
			break;
		case TAG_Float:
			buffer->write(&payload_float);
			break;
		case TAG_Byte_Array: {
			uint32_t len = (uint32_t)payload_byteArray->data.size();
			buffer->write(&len);
			for (uint32_t i = 0; i < len; i++) {
				char character = payload_byteArray->data[i];
				buffer->write(&character);
			}

			break;
		}
		case TAG_String: {
			uint8_t len = (uint8_t )payload_string->data.size();
			buffer->write(&len);
			for (int i = 0; i < len; i++) {
				char character = payload_string->data[i];
				buffer->write(&character);
			}
			break;
		}
		case TAG_List: {
			uint8_t type = payload_tagList->dataType;
			uint16_t len = (uint16_t)payload_tagList->data.size();

			buffer->write(&type);
			buffer->write(&len);
			for (auto it = payload_tagList->data.begin(); it != payload_tagList->data.end(); ++it) {
                (*it)->writeToBuffer(buffer);
			}

			break;
		}
		case TAG_Compound: {
			for (auto it = payload_tagCompound->data.begin(); it != payload_tagCompound->data.end(); ++it) {
				it->second->writeToBuffer(buffer);
                uint16_t cpy = it->first;
				buffer->write(&cpy);
			}
			unsigned char tagEnd = Tag::TAG_End;
			buffer->write(&tagEnd);
			break;
		}
		case TAG_UByte:
			buffer->write(&payload_ubyte);
			break;
        case TAG_UInt32:
            buffer->write(&payload_uint);
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





