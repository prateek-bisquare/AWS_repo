import json
import boto3
import time

s3 = boto3.client('s3')

def lambda_handler(event, context):
    bucket_name = "s3gatewayhardik"
    folder_name = "testgate"  # Specify your folder name here
    key_name = folder_name + "/" + str(int(time.time()))  # Assuming you imported time module
    content = json.dumps(event)  # Uncomment this statement for testing in lambda
    # content = json.dumps(event['queryStringParameters'])  # Uncomment this statement after integration with API Gateway
    # Keep only one of the above uncommented!
    data=json.loads(content)
    val=data.get("body").split('=')[1]
    #bc_value = data.get("body")
    

    params = {'Bucket': bucket_name, 'Key': key_name, 'Body': val}

    try:
        response = s3.put_object(**params)
        print("Successfully saved object to", bucket_name + "/" + key_name, "and data =", json.dumps(content))
    except Exception as e:
        print(e)
