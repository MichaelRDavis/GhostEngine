#pragma once

template<typename Type, typename Elements>
class TArray
{
public:
	TArray();
	~TArray();

private:
	Type m_array[Elements];
};