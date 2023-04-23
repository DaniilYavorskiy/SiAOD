#include "tree.h"
#include <time.h>
#include <algorithm>
#include <random>
#include <iomanip>

void showInfo(const Tree &tree) {
    std::cout << "Size: " << tree.size()
              << "\nHeight: " << tree.height()
              << "\nMedium height: " << tree.mediumHeight()
              << "\nCheck sum: " << tree.checkSum()
              << "\nIn-order traversal (L to R): ";
    tree.printLNR();
}

void printTable(const Tree &a, const Tree &b, const Tree &c) {
    using std::setw;
    std::cout << "\nn = 100  Size  Check Sum  Height  Medium height\n"
              << "ISDP   " << setw(6) << a.size() << setw(11) << a.checkSum() << setw(8) << a.height()
              << setw(15) << a.mediumHeight() << '\n'
              << "SDP recur" << setw(4) << b.size() << setw(11) << b.checkSum() << setw(8) << b.height()
              << setw(15) << b.mediumHeight() << '\n'
              << "SDP point" << setw(4) << c.size() << setw(11) << c.checkSum() << setw(8) << c.height()
              << setw(15) << c.mediumHeight() << '\n';
}
int randmasselm(int n,int arr[]){
	int nnew,k;
        for(int i=0;i<n;i++){
    	int rid=0;
    	while(rid!=1){
        k=rand()%999;
        int pre=0;
        for(int j=0;j<i;j++){
        	if(arr[j]==k){
        		pre=1;
        		break;
        	}
        }
        if(pre==0){arr[i]=k; rid=1;
        }
      }
    }
}

int main() {
    int n = 100;
    srand(time(NULL));
    SdpTree recTree, doubleTree;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
        randmasselm(i,arr);
    }
    IsdpTree isdpTree(arr, n);
    auto rng = std::default_random_engine{};
    std::shuffle(&arr[0], &arr[n], rng);
    for (auto i : arr) {
        recTree.addRec(i);
        doubleTree.addDouble(i);
    }

    std::cout << "ISDP:\n";
    showInfo(isdpTree);
    std::cout << "\nSDP Recoursive method:\n";
    showInfo(recTree);
    std::cout << "\nSDP Pointer method:\n";
    showInfo(doubleTree);

    std::cout << "\n";
    printTable(isdpTree, recTree, doubleTree);
}
