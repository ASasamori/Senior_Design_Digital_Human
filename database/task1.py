from google.colab import auth

auth.authenticate_user()

# @markdown Please fill in the value below with your GCP project ID and then run the cell.

# Please fill in these values.
project_id = "sanguine-orb-441020-p6"  # @param {type:"string"}

# Quick input validations.
assert project_id, "⚠️ Please provide a Google Cloud project ID"

# Configure gcloud.
# see shell file
# !gcloud config set project {project_id}