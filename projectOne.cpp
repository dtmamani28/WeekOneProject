#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <ostream>

struct Color {
	float red, green, blue;

	static Color random() {
		static std::mt19937 engine{ std::random_device{}() };
		static std::uniform_real_distribution<float> dist{0,1};

		return Color{ dist(engine), dist(engine), dist(engine) };
	}
};

struct less_than_blue
{
	inline bool operator() (const Color& color1, const Color& color2) {
		return(color1.blue < color2.blue);
	}
};

void colorSink(std::unique_ptr<Color> color) {
	std::cout << "Success!\n";
}

std::ostream& operator<<(std::ostream & out, const Color& c) {
	out << "COLOR(" << c.red << ", " << c.green << ", " << c.blue << ")";
	return out;
}

int main() {
	std::cout << "Hello, World\n";

 	auto c = Color::random();
	std::cout << "First color is: " << c <<"\n";

	std::vector<Color> colors;
	for (int i = 0; i < 10; i++) {
		colors.push_back(Color::random());
	}

	std::cout << "colors intial order: [\n";
	for (int i = 0; i < colors.size(); i++) {
		std::cout <<"	" << colors.at(i) << "\n";
	}
	std::cout << "]\n";

	std::cout << "colors reversed: [\n";
	std::reverse(colors.begin(), colors.end());
	for (int i = 0; i < colors.size(); i++) {
		std::cout << "	" << colors.at(i) << "\n";
	}
	/*for (int i = 1; i < colors.size(); i++) {
		std::cout << "	" << colors.at(colors.size()-i) << "\n";
	}*/
	std::cout << "]\n";

	auto tempLocate = colors.at(0);
	auto tempSum = tempLocate.red + tempLocate.green + tempLocate.red;
	for (int i = 0; i < colors.size(); i++) {
		auto variableSum = colors.at(i).red + colors.at(i).green + colors.at(i).red;
		if (variableSum >! tempSum) {
			tempLocate = colors.at(i);
		}
	}

	//auto minSum = std::min_element(colors.at(i).begin(), colors.end());

	std::cout << "the darkest color is " << tempLocate <<"\n";

	std::sort(colors.begin(), colors.end(), less_than_blue());

	std::cout << "colors sorted by 'blue' value:[\n";
	for (int i = 0; i < colors.size(); i++) {
		std::cout << "	" << colors.at(i) << "\n";
	}


}
