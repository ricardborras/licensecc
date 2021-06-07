/*
 * plaintext_strategy.cpp
 *
 *  Created on: Jun 7, 2021
 *      Author: rborras
 */
#include <string.h>
#include "../os/os.h"
#include "plaintext_strategy.hpp"
#include "../base/base64.h"
#include <fstream>


using namespace std;
namespace license {
namespace hw_identifier {


static FUNCTION_RETURN generate_plain_text_id(vector<array<uint8_t, HW_IDENTIFIER_PROPRIETARY_DATA>> &plain_text_id) {

	// Look for plain text defined in a environment var
	char *env_var_value = getenv(LCC_LICENSE_DATA_PLAIN_TEXT_LOCATION);
	if (env_var_value != nullptr && env_var_value[0] != '\0') {
		
		ifstream ifs(env_var_value);
  		string file_content_str((istreambuf_iterator<char>(ifs) ),
                       		(istreambuf_iterator<char>()    ) );

		vector<uint8_t> binary_content =  unbase64(file_content_str);

		array<uint8_t, HW_IDENTIFIER_PROPRIETARY_DATA> a_file_content_id = {};

		size_t size = min((size_t) HW_IDENTIFIER_PROPRIETARY_DATA, binary_content.size());
		for(size_t s = 0; s < size; ++s)
		{
			a_file_content_id[s] = binary_content[s];
		}		

		plain_text_id.push_back(a_file_content_id);
		
	}

	return plain_text_id.size() == 1 ? FUNC_RET_OK : FUNC_RET_NOT_AVAIL;
}

PlainTextStrategy::~PlainTextStrategy() {}

LCC_API_HW_IDENTIFICATION_STRATEGY PlainTextStrategy::identification_strategy() const {
	return LCC_API_HW_IDENTIFICATION_STRATEGY::STRATEGY_PLAINTEXT;
}

std::vector<HwIdentifier> PlainTextStrategy::alternative_ids() const {
	vector<array<uint8_t, HW_IDENTIFIER_PROPRIETARY_DATA>> data;
	FUNCTION_RETURN result = generate_plain_text_id(data);
	vector<HwIdentifier> identifiers;
	if (result == FUNC_RET_OK) {
		identifiers.reserve(data.size());
		for (auto &it : data) {
			HwIdentifier pc_id;
			pc_id.set_identification_strategy(identification_strategy());
			pc_id.set_data(it);
			identifiers.push_back(pc_id);
		}
	}
	return identifiers;
}

}  // namespace hw_identifier
} /* namespace license */
