#include <gtest/gtest.h>
#include <opengltext.h>
#include <iostream>
#include <string>

const std::string PROJECT_ROOT = "../../../";
const std::string DIRECTORY_ASSETS = PROJECT_ROOT + "assets/";
const std::string DIRECTORY_FONTS = DIRECTORY_ASSETS + "fonts/";

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	std::cin.get();
	return result;
}

TEST(TestInit, Ok)
{
	gltext_error_t error = gltext_init();
	ASSERT_EQ(error, GLTEXT_ERROR_NONE);
}

class TestLoadFont : public testing::Test
{
public:
	TestLoadFont()
	{
		gltext_init();
	}

	~TestLoadFont()
	{
		gltext_quit();
	}
};

TEST_F(TestLoadFont, FileNotFound)
{
	gltext_font_t* font = NULL;
	gltext_error_t error = gltext_create_font("nonexisting.ttf", &font);
	EXPECT_EQ(error, GLTEXT_ERROR_FREETYPE);
}

TEST_F(TestLoadFont, UnknownFormat)
{
	gltext_font_t* font = NULL;
	gltext_error_t error = gltext_create_font((DIRECTORY_FONTS + "test_unknownformat.ttf").c_str(), &font);
	EXPECT_EQ(error, GLTEXT_ERROR_FREETYPE);
}

TEST_F(TestLoadFont, CorruptedFormat)
{
	gltext_font_t* font = NULL;
	gltext_error_t error = gltext_create_font((DIRECTORY_FONTS + "test_corruptedformat.ttf").c_str(), &font);
	EXPECT_EQ(error, GLTEXT_ERROR_FREETYPE);
}

TEST_F(TestLoadFont, Success)
{
	gltext_font_t* font = NULL;
	gltext_error_t error = gltext_create_font((DIRECTORY_FONTS + "FreeSans.ttf").c_str(), &font);
	EXPECT_EQ(error, GLTEXT_ERROR_NONE);
}