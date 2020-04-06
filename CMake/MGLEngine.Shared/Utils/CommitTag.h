#pragma once
class CommitTag
{
	static long SourceIdGenerator;
	long sourceId;
	long changeId;

public:

	CommitTag()
	{
		sourceId = 0;
		changeId = 0;
	}
	static CommitTag NewTagChain() {
		CommitTag cm;
		cm.sourceId = SourceIdGenerator++;
		cm.changeId = 0;
		return cm;
	}
	



	void Next()
	{
		changeId++;
	}

	bool operator != (const CommitTag & c)
	{
		return c.sourceId != sourceId || c.changeId != changeId;
	}

	bool operator == (const CommitTag& c)
	{
		return c.sourceId == sourceId && c.changeId == changeId;
	}


};
