#include "mydb.h"


DBMysqlConn::DBMysqlConn(const char* host,const char* user,const char* passwd,const char* db_name) {
    MYSQL *sql_res;

    if (!(sql_res = mysql_init(&mysql))) {
        cout << "mysql_init(): " << mysql_error(&mysql) << endl;
        assert(sql_res);
    }
    
    if (!(sql_res == mysql_real_connect(&mysql,host,user,passwd,db_name,0,NULL,0))) {
        cout << "mysql_real_connect():" << mysql_error(&mysql) << endl;
        assert(sql_res);
    }

    cout << "connected to MySQL.\n";
}


bool DBMysqlConn::db_insert(const string& sqlstr) {
    cout << "inserting with sql: " << sqlstr << "...\n";
    int flag = mysql_real_query(&mysql, sqlstr.c_str(), sqlstr.size());
    //if successful return 0
    if(flag != 0) {
        cout << " mysql_real_query(): " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}


bool DBMysqlConn::db_update(const string& sqlstr) {
    cout << "updating with sql: " << sqlstr << "...\n";
    int flag = mysql_real_query(&mysql, sqlstr.c_str(), sqlstr.size());
    //if successful return 0
    if(flag != 0) {
        cout << " mysql_real_query(): " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}


vector<vector<string>> DBMysqlConn::db_select(const string& sqlstr) {

    cout << "selecting with sql: " << sqlstr << "...\n";
    int flag = mysql_real_query(&mysql, sqlstr.c_str(), sqlstr.size());
    
    if(flag != 0) {
        cout << " mysql_real_query(): " << mysql_error(&mysql) << endl;
        return {};
    }

    MYSQL_RES* res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return {};
    }

    int m = mysql_num_rows(res);
    int n = mysql_num_fields(res);

    vector<vector<string>> res_table(m, vector<string>(n));

    for (int i = 0; i < m; i++) {
        MYSQL_ROW row = mysql_fetch_row(res);
        for (int j = 0; j < n; j++) {
            res_table[i][j] = row[j];
        }
    }

    return res_table;
}


void DBMysqlConn::db_close() {
    mysql_close(&mysql);
}


DBMysqlConn::~DBMysqlConn() {
    db_close();
}


// *************** SQL connection pool *******************
SqlConnPool::SqlConnPool() {
    useCount_ = 0;
    freeCount_ = 0;
}


SqlConnPool* SqlConnPool::Instance(const Config& config) {
    static SqlConnPool *connPool = nullptr;
    if (!connPool) {
        connPool = new SqlConnPool;
        connPool->init(config);
    }
    return connPool;
}


void SqlConnPool::init(const Config& config) {
    for (int i = 0; i < config.connSize; i++) {
        cout << "initing connection " << i << "...\n";
        DBMysqlConn *sql = new DBMysqlConn(config.host.c_str(), config.user.c_str(), 
                            config.pwd.c_str(), config.dbName.c_str());
        connQue_.push(sql);
    }

    MAX_CONN_ = config.connSize;
    sem_init(&semId_, 0, MAX_CONN_);
}


DBMysqlConn* SqlConnPool::GetConn() {
    if(connQue_.empty()){ return nullptr; }

    DBMysqlConn *sql = nullptr;

    sem_wait(&semId_);
    {
        lock_guard<mutex> locker(mtx_);
        sql = connQue_.front(); connQue_.pop();
    }

    return sql;
}


void SqlConnPool::FreeConn(DBMysqlConn* sql) {
    assert(sql);

    lock_guard<mutex> locker(mtx_);
    connQue_.push(sql);

    sem_post(&semId_);
}


void SqlConnPool::ClosePool() {
    lock_guard<mutex> locker(mtx_);
    while(!connQue_.empty()) {
        auto item = connQue_.front(); connQue_.pop();
    }

    mysql_library_end();
}


int SqlConnPool::GetFreeConnCount() {
    lock_guard<mutex> locker(mtx_);
    return connQue_.size();
}


SqlConnPool::~SqlConnPool() {
    ClosePool();
}


SqlConnWrapper::SqlConnWrapper(SqlConnPool *pool_) {
    pool = pool_;
    conn = pool->GetConn();
}


SqlConnWrapper::~SqlConnWrapper() {
    if (conn) {
        pool->FreeConn(conn);
    }
}
