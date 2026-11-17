#pragma once
#include <MGLEngine.Shared/Interfaces/GLID.h>
#include <vector>

class BufferWriteCommand {

public:
	std::vector<std::byte> vData;
	GLID glId;

};
class CommandQueue {
	public:
		std::vector<BufferWriteCommand> uboCommands;

};
