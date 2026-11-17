#pragma once
#include <MGLEngine.Shared/Interfaces/GLID.h>
#include <MGLEngine.Shared/Utils/Pool.h>
#include <vector>

class BufferWriteCommand {

public:
	Pool<std::vector<std::byte>>::Handle  dataHandle;
	GLID glId;

};
class CommandQueue {
	public:
		std::vector<BufferWriteCommand> uboCommands;
};


