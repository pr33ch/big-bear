#include "gtest/gtest.h"
#include "http_request.h"

class HttpRequestTest : public ::testing::Test {
  protected:
  	HttpRequest request;
};

TEST_F(HttpRequestTest, partialRequest)
{
	std::string firstHalf = "GET /static/bearlist.txt HT";

	bool isParseCompleted = request.parseHttpRequest(firstHalf);
	// The request without \n is considered malformed, therefore the parse is completed
	EXPECT_TRUE(isParseCompleted);
	EXPECT_FALSE(request.isComplete);
}

TEST_F(HttpRequestTest, requestInTwoPieces)
{
	std::string firstHalf = "GET /static/bearlist.txt HT";
	std::string secondHalf = "TP/1.1\r\nUser-Agent: nc/0.0.1\r\nHost: 127.0.0.1\r\nAccept: */*\r\n\r\n";

	request.parseHttpRequest(firstHalf);
	bool isParseCompleted = request.finishParsingRequest(secondHalf);

	EXPECT_TRUE(isParseCompleted);
	EXPECT_TRUE(request.isComplete);
	EXPECT_STREQ(request.httpVersion.c_str(), "HTTP/1.1");
}

TEST_F(HttpRequestTest, requestInThreePieces)
{
	std::string firstPart = "GET /static/bearlist.txt HT";
	std::string secondPart = "TP/1.1\r\nUse";
	std::string thirdPart = "r-Agent: nc/0.0.1\r\nHost: 127.0.0.1\r\nAccept: */*\r\n\r\n";

	request.parseHttpRequest(firstPart);
	request.finishParsingRequest(secondPart);
	bool isParseCompleted = request.finishParsingRequest(thirdPart);

	EXPECT_TRUE(isParseCompleted);
	EXPECT_TRUE(request.isComplete);
	EXPECT_STREQ(request.headerFields[USER_AGENT].c_str(), "nc/0.0.1");
}