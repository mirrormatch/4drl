
// Using this for actual strings
#include <string>
// stl containers
#include <vector>
#include <list>
#include <map>
#ifndef WIN32
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#include <algorithm>
using namespace std;
#ifndef WIN32
using namespace tr1;
#endif
typedef vector<string> StringVector;

// Because I wanted memset
#include "string.h"

// Other C stdlib stuff that I want
#include <time.h> // for getting a random seed
#include <stdlib.h>

// Our color magic
#include "ColorPairs.h"
