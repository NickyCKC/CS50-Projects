# Generated by Django 4.0.3 on 2022-09-03 13:03

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0009_alter_bid_user_alter_comment_author_and_more'),
    ]

    operations = [
        migrations.RenameField(
            model_name='category',
            old_name='categoryName',
            new_name='category_name',
        ),
    ]
