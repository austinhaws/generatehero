gcloud config set project causal-block-97013
gcloud builds submit --tag gcr.io/causal-block-97013/generatehero
gcloud run deploy generatehero \
  --image gcr.io/causal-block-97013/generatehero \
  --platform managed \
  --region us-central1 \
  --allow-unauthenticated
