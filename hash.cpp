#include <iostream>
#include <boost/math/distributions/chi_squared.hpp>
#include <cstdint>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

vector<int> hashes(65536);
int bins[65];

void test(int n){

	for (int i = 0; i < n; ++i)
		cout << hashes.at(i) << endl;
		
}

void testbins(){

	for (int i = 0; i < 65; ++i)
		cout << bins[i] << endl;
		
}

float pearson_test(){

	double expected = 99170 / 65536.0;
	double c2 = 0;
	for (int i = 0; i < 65536; ++i)
		c2 += pow(expected - hashes[i], 2) / expected;

	boost::math::chi_squared c2d(65535.0);
	float p = boost::math::cdf(c2d, c2);

	return p = (1 - p) * 100.0;
	
}

void seperate_into_bins(){

	// splitting up the hashes into 64 equal sized bins, and 1 bin that is slightly larger
	int count;
	for (int i = 0; i < 64; ++i) {

		count = 0;
		for (int j = i*1008; j < (i + 1) * 1008; ++j){
			count += hashes.at(j);
		}
		bins[i] = count;
	}
	
	count = 0;
	for (int j = 64 * 1008; j < 65536; ++j)
		count += hashes.at(j);
	bins[64] = count;

}

void output_bins_graph(string graph){

	cout << "Here is a graph displaying the distribution of the " << graph << " hash." << endl;
	cout << "Each number to the left of the graph represents a \"bin\" of size 1008 (with bin 64 being of size 1024)." << endl;
	cout << "Each star represents 50 keys that were hashed to a value in that bin." << endl;
	cout << "An evenly distributed hash will have 20-21 per bin approximately." << endl;
	cout << "__________________________________________________________________________________________________________________" << endl;

	for (int i = 0; i < 65; ++i){
		cout << i << "\t| ";
		int numberOfStars = bins[i] / 50;

		if (numberOfStars > 100)
			cout << "This bin contains more than 5 times the amount of hashes than an evenly distributed bin should have.";
		else
			for (int j = 0; j < numberOfStars; ++j)
				cout << '*';

		cout << endl;
	}

	cout << "\nThe probability that the hashes are not far from a uniform distribution is: " << fixed << setprecision(2) << pearson_test() << "%.\n";

}

void distribution_table(string graph){

	seperate_into_bins();
	output_bins_graph(graph);
	
}

void hash_string_length(){

	string str;
	ifstream inStream;
	inStream.open("/usr/share/dict/words");

	if (inStream.is_open()) {
		while (getline(inStream, str)){
			inStream >> str;

			uint16_t h = str.length() % 65536;	// calculating hash

			hashes.at(h)++;
		}

		distribution_table("string length");

		hashes.clear();
		
	}
}

void hash_first_character(){

	string str;
	ifstream inStream;
	inStream.open("/usr/share/dict/words");

	if (inStream.is_open()) {
		while (getline(inStream, str)){
			inStream >> str;

			uint16_t h = str[0];	// calculating hash

			hashes.at(h)++;
		}

		distribution_table("first character");

		hashes.clear();
		
	}
}

void hash_sum_of_characters(){

	string str;
	ifstream inStream;
	inStream.open("/usr/share/dict/words");

	if (inStream.is_open()) {
		while (getline(inStream, str)){
			inStream >> str;
			uint16_t h = str[0];

			for (int next = 1; next < str.length(); ++next)	// calculating hash
				h = (h + str[next]) % 65536;

			hashes.at(h)++;
		}

		distribution_table("additive checksum");

		hashes.clear();
		
	}
}

void hash_remainder(){

	string str;
	ifstream inStream;
	inStream.open("/usr/share/dict/words");

	if (inStream.is_open()) {
		while (getline(inStream, str)){
			inStream >> str;
			uint16_t h = str[0] + 128;

			for (int next = 1; next < str.length(); ++next)	// calculating hash
				h = (256 * h + str[next] + 128) % 65413;

			hashes.at(h)++;
		}

		distribution_table("remainder");

		hashes.clear();
		
	}
}

void hash_multiplicative(){

	string str;
	ifstream inStream;
	inStream.open("/usr/share/dict/words");

	if (inStream.is_open()) {
		while (getline(inStream, str)){
			inStream >> str;
			double h = str[0];

			for (int i = 0; i < str.length(); ++i)	// calculating hash
				h = fmod(256 * h + 0.6180339887 * str[i], 1);

			h *= 65536;
			hashes.at(uint16_t(h))++;
		}

		distribution_table("multiplicative");

		hashes.clear();
		
	}
}

int main(){

	int input;
	cout << "Please enter the kind of hash function that you would like to test.\nEnter 1 for a string length hash.\nEnter 2 for a first character hash.\nEnter 3 for an additive checksum hash.\nEnter 4 for a remainder hash.\nEnter 5 for a multiplicative hash.\nEnter 6 to exit the program.\n";
	cin >> input;

	switch (input){
	case 1:
		system("CLS");
		hash_string_length();
		break;
	case 2:
		system("CLS");
		hash_first_character();
		break;
	case 3:
		system("CLS");
		hash_sum_of_characters();
		break;
	case 4:
		system("CLS");
		hash_remainder();
		break;
	case 5:
		system("CLS");
		hash_multiplicative();
		break;
	case 6:
		system("CLS");
		return 0;
	default:
		cout << "That was an invalid choice, please try again!" << endl;
	}

	cout << endl;
	system("PAUSE");
    return 0;
    
}