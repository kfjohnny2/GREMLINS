class StoragePool{

public:

virtual ~StoragePool ();

virtual void *Allocate ( size_t ) = 0;

virtual void Free ( void * ) = 0;
};