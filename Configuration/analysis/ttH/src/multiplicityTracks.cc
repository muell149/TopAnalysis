#include <iostream>
#include <sstream>
#include <vector> 

int multiplicityTracks (int jetIdx, const std::vector<int> jetTrackIndex)
{
	int multiplicity=0;
		for (size_t i_track=0; i_track!=jetTrackIndex.size();i_track++)
		{
			if (jetTrackIndex.size()==0) break;
			int trackIdx = jetTrackIndex.at(i_track);
			if (trackIdx == jetIdx) multiplicity++;
		}
	return multiplicity;
}//end of function