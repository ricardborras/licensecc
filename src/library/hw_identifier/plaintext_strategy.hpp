/*
 * plaintext_strategy.hpp
 *
 *  Created on: Jun 7, 2021
 *      Author: rborras
 */

#ifndef SRC_LIBRARY_PC_IDENTIFIER_PLAINTEXT_STRATEGY_HPP_
#define SRC_LIBRARY_PC_IDENTIFIER_PLAINTEXT_STRATEGY_HPP_

#include "identification_strategy.hpp"

namespace license {
namespace hw_identifier {

/**
 * @brief HW identifier is determined by a plain text file content
 * 
 */
class PlainTextStrategy : public IdentificationStrategy {
public:
	inline PlainTextStrategy(){};
	virtual ~PlainTextStrategy();
	virtual LCC_API_HW_IDENTIFICATION_STRATEGY identification_strategy() const;
	virtual std::vector<HwIdentifier> alternative_ids() const;
};

}  // namespace hw_identifier
} /* namespace license */

#endif /* SRC_LIBRARY_PC_IDENTIFIER_PLAINTEXT_STRATEGY_HPP_ */
