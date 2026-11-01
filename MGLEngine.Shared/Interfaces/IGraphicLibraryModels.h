#pragma once
#include <MGLEngine.Shared/Interfaces/GLID.h>
#include <vector>

class BufferWriteCommand {

public:
	std::vector<std::byte> vData;
	GLID glId;

};
struct CommandQueue {
	std::vector<BufferWriteCommand> uboCommands;
};
