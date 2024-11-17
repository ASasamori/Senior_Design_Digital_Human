from langchain_google_cloud_sql_pg import PostgresLoader, PostgresEngine, Column


project_id_init="sanguine-orb-441020-p6"
instance_init="langchain-quickstart-instance"
region_init="us-central1"
database_init="ec463-temp-database"
user_init="postgres"
password_init="*****"

pg_engine = PostgresEngine.from_instance(
    project_id=project_id_init,
    instance=instance_init,
    region=region_init,
    database=database_init,
    user=user_init,
    password=password_init,
)