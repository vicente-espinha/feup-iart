/*
 * Print time
 */
// Something like GetTickCount but portable
// It rolls over every ~ 12.1 days (0x100000/24/60/60)
// Use GetMilliSpan to correct for rollover

#include "utils.h"

using namespace std;

int GetMilliCount(){

	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}
//---------------------------------------------------------------------------

int GetMilliSpan(int nTimeStart){

	int nSpan = GetMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}
//---------------------------------------------------------------------------


vector<string> splitString(string rua){
	string buf;
	stringstream ss;
	ss.str(rua);

	vector<string> ret;

	while (ss >> buf)
		ret.push_back(buf);

	return ret;

}

string concatenateStrings(vector<string> vec, int num, int first_pos){
	stringstream ss;
	for(int i = 0; i< num ; i++){
		if(i != num -1)
			ss << vec.at(first_pos + i) << " ";
		else
			ss << vec.at(first_pos + i);
	}

	return ss.str();
}

vector<int> getKeys(multimap<int, int> mmap){
	vector<int> ret;
	multimap<int, int>::const_iterator it = mmap.begin();
	ret.push_back(it->first);
	int lastkey = it->first;
	++it;

	while (it != mmap.end()) {
		if (lastkey < it->first) {
			ret.push_back(it->first);
			lastkey = it->first;
		}
		++it;
	}
	return ret;

}

vector<int> getValues(multimap<int, int> mmap, int key){
	vector<int> ret;
	typedef std::multimap<int, int>::iterator MMAPIterator;
	pair<MMAPIterator, MMAPIterator> result = mmap.equal_range(key);
	for (MMAPIterator it = result.first; it != result.second; it++)
		ret.push_back(it->second);

	return ret;
}

