#include <iostream>

int main(){
	int i = 0;
	if(&i==&(++i)){
		std::cout<<"yes \n";
	}else;

	return 0;
}
