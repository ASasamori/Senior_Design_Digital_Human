# %pip install --upgrade --quiet langchain-google-cloud-sql-pg langchain-google-vertexai langchain

# integrating LLM / Cloud
# Separated into tasks and running respective shell commands as necessary


# task 1
project_id="sanguine-orb-441020-p6"
python init.py
# end task 1

gcloud config set project $project_id

# add permissions to the user
current_user="andrewsasamori@gmail.com"

gcloud auth list --filter=status:ACTIVE --format="value(account)"
gcloud projects add-iam-policy-binding $project_id \
  --member=user:$current_user \
  --role="roles/cloudsql.client"

# echo "We have added the necessary permissions to the user"

# Enable GCP services
gcloud services enable sqladmin.googleapis.com aiplatform.googleapis.com


# consider maybe integrating the below into one python script

# starting to integrate the different use cases
# task 2 - use case 1
python case1.py
# end task 2

# task 3 - use case 2
python case2.py
# end task 3

# task 4 - use case 3
python case3.py
# end task 4

# task 5 - conversation
python conversation.py
# end task 5