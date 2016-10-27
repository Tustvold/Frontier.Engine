#pragma once

#include "Frontier.h"
#include "CompressionBuffer.h"
#include <unordered_map>
#include <vector>

struct Tag {
	typedef enum {
		TAG_End = 0, //Serves no purpose other than to denote the end of a compound tag
		TAG_Byte = 1, //A single signed byte
		TAG_Int16 = 2, //A single signed short
		TAG_Int32 = 3, //A single signed integer
		TAG_Float = 5, //A signed float
		TAG_String = 6, //A UTF-8 string - prepended with a Int16 for size
		TAG_Byte_Array = 7, //An array of unnamed bytes - named - prepended with a Int16 for size
		TAG_Compound = 8, //A list of fully formed tags - named - ends with TAG_End
		TAG_List = 9, //A list of unnamed tags of the same type - it is prepended with a Int16 for size
		TAG_UByte = 10, //A single unsigned byte
        TAG_UInt32 = 11, // A single unsigned integer
	} TagType;

	struct tagListData {
		uint8_t dataType;

		tagListData() {
			dataType = 0;
		}

		bool addTag(std::unique_ptr<Tag>&& tag) {
			if (dataType == 0)
				dataType = tag->type;
			if (dataType != tag->type)
				return false;

			tag->listed = true;
			data.push_back(std::move(tag));
			return true;
		}

		Tag *getTag(uint16_t index) {
			if (index < data.size())
				return data[index].get();
			return NULL;
		}

		std::vector<std::unique_ptr<Tag>> data;

	};

	struct tagByteArrayData {
        std::vector<unsigned char> data;
	};

	struct tagCompoundData {

		void addTag(std::unique_ptr<Tag>&& tag, uint16_t identifier) {
			data[identifier] = std::move(tag);
		}

		Tag *getTag(uint16_t key, uint8_t type) {
			auto got = data.find(key);
			if (got == data.end())
				return NULL;
            auto ret = got->second.get();
            FTAssert(ret->type == type, "Invalid Type");
			return ret;
		}

		tagCompoundData() {

		}

		std::unordered_map<uint16_t, std::unique_ptr<Tag>> data;
	};

    struct tagStringData {
        std::string data;

        tagStringData() {

        }

        tagStringData(size_t size) : data(size, ' ') {

        }
    };

	union {
		int8_t payload_byte;
		int16_t payload_short;
		int32_t payload_int;
		float payload_float;
		uint8_t payload_ubyte;
        uint32_t payload_uint;

        tagStringData *payload_string;
		tagByteArrayData *payload_byteArray;
		tagListData *payload_tagList;
		tagCompoundData *payload_tagCompound;

	};

	Tag(uint8_t _type);

	Tag(CompressionBuffer *buffer, uint8_t _type = 0);

	~Tag() {
		if (type == TAG_Compound)
			delete payload_tagCompound;
		else if (type == TAG_Byte_Array)
			delete payload_byteArray;
		else if (type == TAG_List)
			delete payload_tagList;
        else if (type == TAG_String)
            delete payload_string;
	}

	//appends the tag data to the buffer
	void writeToBuffer(CompressionBuffer *buffer);

	void logStructure(std::stringstream& str, uint16_t indent = 0);

	uint8_t type;
	//Whether the tag is in a list
	bool listed;
};
