#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

typedef unsigned long long ULLONG;

ULLONG vectAccumulate(std::vector<ULLONG>& vect)
{
	ULLONG total{ 0 };

	for (const auto& item : vect)
	{

		total += item;

	}

	return total;
}

int main()
{
	constexpr int number_of_threads = 10000;    //1, 5,  3 , 6 , 8 , 9 , 5 , 10000
	constexpr ULLONG  number_of_items = 1000 * 1000 * 1000; //5, 1, ,7 , 21 ,21 ,26, 10 ,1000 * 1000 * 1000
	constexpr ULLONG  step = number_of_items / number_of_threads;

	ULLONG  NUM = number_of_threads;

	if (number_of_items % number_of_threads != 0)
	{
		NUM = number_of_threads - 1;
	}

	ULLONG  counter = 1;
	size_t  index = 0;
	ULLONG  start = 0;
	ULLONG  end = 0;
	std::vector<std::thread> workers;
	std::vector<ULLONG> vectSum;
	vectSum.reserve(number_of_threads);
	//Assigning a task to a specific thread

	for (; index < NUM; ++index, counter += step)
	{
		start = counter;
		end = counter + step - 1;

		std::cout << start << ", " << end << ", " << index << '\n';
		workers.emplace_back(

			[&](ULLONG  start_, ULLONG  end_) -> void {
				ULLONG sum{ 0 };
				for (ULLONG i = start_; i <= end_; ++i)
				{

					sum += i;
				}

				vectSum.push_back(sum);
			}
		, start, end);


	}

	if (number_of_items % number_of_threads != 0)
	{
		std::cout << counter << "  ," << number_of_items << ", " << index << '\n';
		workers.emplace_back(

			[&]() -> void {
				ULLONG sum{ 0 };
				for (ULLONG i = counter; i <= number_of_items; ++i)
				{
					sum += i;
				}

				vectSum.push_back(sum);
			}

		);


	}
	std::for_each(workers.begin(), workers.end(),

		[](std::thread& th) -> void
		{th.join(); }

	);


	std::cout << "total: " << vectAccumulate(vectSum) << "\n";



}