
int	get_new_state(int current_state, int token)
{
	const int	matrix[4][9] = {		//-   ***estados***
		{1, 1, 1, 1, 2, 2, 2, 2, 4},	//- 0.estado inicial
		{1, 1, 1, 1, 2, 2, 2, 2, 3},	//- 1.estado words
		{1, 1, 1, 1, 4, 4, 4, 4, 4},	//- 2.estado redirects
		{1, 1, 1, 1, 2, 2, 2, 2, 4},	//- 3.estado pipe
		{4, 4, 4, 4, 4, 4, 4, 4, 4},	//- 4.estado err
	};//-W  $  "  '  <  << >  >> |
	//-  0, 1, 2, 3, 4, 5, 6, 7, 8
}

