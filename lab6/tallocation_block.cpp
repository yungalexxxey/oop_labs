#include "tallocation_block.h"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count)
    : _size(size), _count(count)
{
  _used_blocks = (char *)malloc(_size * _count);

  for (size_t i = 0; i < _count; ++i)
  {
    _free_blocks.insert(_used_blocks + i * _size);
  }
  _free_count = _count;
  std::cout << "TAllocationBlock: Memory init" << std::endl;
}

void TAllocationBlock::print()
{
  _free_blocks.print();
}

void *TAllocationBlock::allocate()
{
  void *result = nullptr;

  if (_free_count > 0)
  {
    result = _free_blocks.get();
    _free_blocks.remove(result);
    _free_count--;
    std::cout << "TAllocationBlock: Allocate " << (_count - _free_count);
    std::cout << " of " << _count << std::endl;
  }
  else
  {
    std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
  }

  return result;
}

void TAllocationBlock::deallocate(void *pointer)
{
  std::cout << "TAllocationBlock: Deallocate block " << std::endl;
  _free_blocks.insert(pointer);
  _free_count++;
}

bool TAllocationBlock::has_free_blocks()
{
  return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock()
{
  if (_free_count < _count)
  {
    std::cout << "TAllocationBlock: Memory leak?" << std::endl;
  }
  else
  {
    std::cout << "TAllocationBlock: Memory freed" << std::endl;
  }
  while (!_free_blocks.empty())
  {
    _free_blocks.remove(_free_blocks.get());
  }
  free(_used_blocks);
}
