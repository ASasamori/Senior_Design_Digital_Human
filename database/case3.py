from langchain_google_cloud_sql_pg import PostgresChatMessageHistory, PostgresEngine

message_table_name = "message_store"
project_id = "sanguine-orb-441020-p6"  
instance_name = "langchain-quickstart-instance"
region = "us-central1"
database_name = "ec463-temp-database"
password = "*****"


pg_engine = PostgresEngine.from_instance(
    project_id=project_id,
    instance=instance_name,
    region=region,
    database=database_name,
    user="postgres",
    password=password,
)

pg_engine.init_chat_history_table(table_name=message_table_name)

chat_history = PostgresChatMessageHistory.create_sync(
    pg_engine,
    session_id="my-test-session",
    table_name=message_table_name,
)

chat_history.add_user_message("Hi!")
chat_history.add_ai_message("Hello there. I'm a model and am happy to help!")

chat_history.messages