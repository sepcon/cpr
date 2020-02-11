#include <gtest/gtest.h>

#include <string>
#include <fstream>
#include <sstream>

#include <cpr/cpr.h>

#include "server.h"

using namespace cpr;

static Server* server = new Server();
auto base = server->GetBaseUrl();

TEST(StreamTests, StringStreamTest) {
    auto url = Url{base + "/header_reflect.html"};

    std::ostringstream oss;
    auto response = cpr::Get(url, ResponseDataStream{oss});
    auto expected_text = std::string{"Header reflect GET"};
    EXPECT_EQ(expected_text, oss.str());
    EXPECT_EQ(url, response.url);
    EXPECT_EQ(200, response.status_code);
    EXPECT_EQ(ErrorCode::OK, response.error.code);
}

TEST(StreamTests, OfstreamStreamTest) {
    const auto html = std::string{"header_reflect.html"};
    auto url = Url{base + "/" + html };

    std::ofstream oss{ html }; // file: ./header_reflect.html

    // ResponseDataStream is alias of DownloadStream
    auto response = cpr::Get(url, DownloadStream{oss});
    oss.close(); // flush all content

    auto expected_text = std::string{"Header reflect GET"};


    std::ifstream ifs{ html };
    auto htmlContent = std::string { // Read content from file back to htmlContent
            std::istreambuf_iterator<char>{ifs},
            std::istreambuf_iterator<char>{} };

    EXPECT_EQ(expected_text, htmlContent);
    EXPECT_EQ(url, response.url);
    EXPECT_EQ(200, response.status_code);
    EXPECT_EQ(ErrorCode::OK, response.error.code);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(server);
    return RUN_ALL_TESTS();

}
