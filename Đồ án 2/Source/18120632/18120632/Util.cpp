#include "Util.h"
#pragma warning(disable: 4996);

void Util::standardized(string& str) {
	if (!str.empty()) {
		while (str[0] == ' ')
			str.erase(str.begin() + 0);

		while (str[str.length() - 1] == ' ')
			str.erase(str.begin() + str.length() - 1);

		for (int i = 0; i < str.length(); ++i)
			if (str[i] == ' ' && str[i + 1] == ' ')
			{
				str.erase(str.begin() + i);
				--i;
			}

		strlwr((char*)str.c_str());

		if (str[0] != ' ')
			if (str[0] >= 97 && str[0] <= 122)
				str[0] -= 32;

		for (int i = 0; i < str.length() - 1; i++)
			if (str[i] == ' ' && str[i + 1] != ' ')
				if (str[i + 1] >= 97 && str[i + 1] <= 122)
					str[i + 1] -= 32;
	}
}

void Util::standardizedUPPERCASE(string& str) {
	standardized(str);

	for (auto& c : str)
		if (c >= 97 && c <= 122)
			c -= 32;
}

bool Util::isIdentityCard(string& str) {
	standardized(str);

	for (auto c : str)
		if (c < '0' || c > '9')
			return false;

	return true;
}