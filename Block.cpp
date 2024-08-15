#include "Block.h"
#include "Define.h"

Block::Block()
{
}

Block::Block(int type, int dire,int color_tmp):blockType(type), blockDire(dire), color(color_tmp){
	m_x = BlockTypeTran[type][dire][0][0];
	m_y = BlockTypeTran[type][dire][0][1];
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (BlockTypeTran[type][dire][j][1] > BlockTypeTran[type][dire][i][1])
				heigh = max(heigh, BlockTypeTran[type][dire][j][1] - BlockTypeTran[type][dire][i][1] + 1);
			else
				heigh = max(heigh, BlockTypeTran[type][dire][i][1] - BlockTypeTran[type][dire][j][1] + 1);
		}
	}
}

int Block::GetBlockType()
{
	return blockType;
}

int Block::GetBlockDire()
{
	return blockDire;
}

int Block::GetBlockX()
{
	return m_x;
}

int Block::GetBlockY()
{
	return m_y;
}

int Block::GetBlockColor()
{
	return color;
}


void Block::BlockInit()
{
}

void Block::BlockCtrl(int keyinput)
{

	if (keyinput == up)
		BlockRevolve();
	else
		BlockMove(keyinput);
}

void Block::BlockMove(int value)
{
	if (value == right) {
		if(edge_right && edge_down)
			m_x++;
	}
	else if (value == left) {
		if (edge_left && edge_down)
			m_x--;
	}
	else
		if(edge_down)
			m_y++;

}

void Block::BlockRevolve()
{
	if(edge_down && revole_bool)
		blockDire = (blockDire + 1) % 4;
}

void Block::BlockDrop()
{
	if (edge_down) m_y++;
}

void Block::SetRightBool(bool value)
{
	edge_right = value;
}

void Block::SetLeftBool(bool value)
{
	edge_left = value;
}

void Block::SetDownBool(bool value)
{
	edge_down = value;
}

void Block::SetRevoleBool(bool value)
{
	revole_bool = value;
}

bool Block::GetDownBool()
{
	return edge_down;
}
