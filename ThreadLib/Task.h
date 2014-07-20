
template < typename codeT, class execStateT>
class Task
{
public:	
	
	Task(const Task < codeT, execStateT>& source)
	{
		m_code = source.m_code;
		m_
	}
	
	Task(codeT code, stateT state)
	{
		m_code = code;
		m_state = state;
	}

	~Task() {}



private:
	codeT m_code;
	execStateT m_state;


};